<div class="form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'question-bank-form',
	'enableAjaxValidation'=>false,
)); ?>

	<p class="note">Fields with <span class="required">*</span> are required.</p>

	<?php echo $form->errorSummary($model); ?>


	<div class="row">
		<?php echo $form->labelEx($model,'question'); ?>
		<?php echo $form->textField($model,'question',array('size'=>60,'maxlength'=>500)); ?>
		<?php echo $form->error($model,'question'); ?>
	</div>
	<script type = "text/javascript">
		function change(s) {
			var selections=document.getElementById('selections');
			var answer=document.getElementById('answer');
//			alert(selections.style.display);
			if (s==1) {
				selections.style.display="none";    
				answer.options.length=0;
				var varItem = new Option('T', 'T');
				answer.options.add(varItem);
				var varItem = new Option('F', 'F');
				answer.options.add(varItem);
			}
			else {
				selections.style.display="block";    
				answer.options.length=0;
				var varItem = new Option('A', 'A');
				answer.options.add(varItem);
				var varItem = new Option('B', 'B');
				answer.options.add(varItem);				
				var varItem = new Option('C', 'C');
				answer.options.add(varItem);				
				var varItem = new Option('D', 'D');
				answer.options.add(varItem);				
			}
			
		}
	</script>
	<div class="row">
		<label for="QuestionBank_type" class="required">Type <span class="required">*</span></label>	
		<select name="QuestionBank[type]" id="QuestionBank_type" onchange = change(this.options[this.options.selectedIndex].value)>
			<option value="0">Selection</option>
			<option value="1">Judge</option>
		</select>			
	</div>

	<div id = "selections">
		<div class="row">
			<?php echo $form->labelEx($model,'selection_a'); ?>
			<?php echo $form->textField($model,'selection_a',array('size'=>60,'maxlength'=>100)); ?>
			<?php echo $form->error($model,'selection_a'); ?>
		</div>

		<div class="row">
			<?php echo $form->labelEx($model,'selection_b'); ?>
			<?php echo $form->textField($model,'selection_b',array('size'=>60,'maxlength'=>100)); ?>
			<?php echo $form->error($model,'selection_b'); ?>
		</div>

		<div class="row">
			<?php echo $form->labelEx($model,'selection_c'); ?>
			<?php echo $form->textField($model,'selection_c',array('size'=>60,'maxlength'=>100)); ?>
			<?php echo $form->error($model,'selection_c'); ?>
		</div>

		<div class="row">
			<?php echo $form->labelEx($model,'selection_d'); ?>
			<?php echo $form->textField($model,'selection_d',array('size'=>60,'maxlength'=>100)); ?>
			<?php echo $form->error($model,'selection_d'); ?>
		</div>
	</div>


<?php /*
	<div class="row">
		<?php echo $form->labelEx($model,'type'); ?>
		<?php echo $form->dropDownList($model,'type',$model->typeOptions,
		array(
			'onchange'=>'show()',
			'ajax'=>array(
				'url'=>$this->createUrl('questionBank/dynamicAnswer'),
				'data'=>array('type'=>'js:this.value'),
				'update'=>'#'.CHtml::activeId($model,'answer'),
				)
			)
		);
		 ?>
		<?php echo $form->error($model,'type'); ?>
	</div>
	*/
?>
	<div class="row">
		<?php echo $form->labelEx($model,'answer'); ?>
		<?php echo $form->dropDownList($model,'answer',$model->getAnswerOptions(0),array('id'=>'answer')); ?>
		<?php echo $form->error($model,'answer'); ?>
	</div>

	<div class="row buttons">
		<?php echo CHtml::submitButton($model->isNewRecord ? 'Create' : 'Save'); ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- form -->
